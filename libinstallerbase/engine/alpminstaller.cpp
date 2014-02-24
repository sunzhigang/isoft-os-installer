#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include "alpminstaller.h"  
#include <regex.h>
#include "ipacman.h"
#include "pkgmeta.h"

using namespace std;

static AlpmInstaller* g_alpm_installer = NULL;

AlpmInstaller::AlpmInstaller(const list<string> &groups, const string &rootdir)
    :_groups(groups), _rootdir(rootdir), _targets(NULL), _nr_total_pkgs(0), _reporter(NULL)
{
    g_alpm_installer = this;
}


AlpmInstaller::~AlpmInstaller()
{
    g_alpm_installer = NULL;
    ipacman_cleanup();
}

static void cb_progress(alpm_progress_t event, const char *pkgname, int percent,
                       size_t howmany, size_t current)
{
    printf("pkgname=%s, percent=%d, howmany=%ld, current=%ld\n", pkgname, percent, howmany, current);
    if (pkgname) {
        g_alpm_installer->reportUpstream(current*100/howmany);
    }

}

bool AlpmInstaller::reportUpstream(int percent)
{
    if (_reporter)
        _reporter(percent);
    return true;
}

bool AlpmInstaller::preprocess()
{
    ipacman_init(_rootdir.c_str(), cb_progress);
    ipacman_add_server("isoft", "file:///PKGS/");

    char buf[1024];
    snprintf(buf, sizeof buf - 1,
            "mkdir -m 0755 -p %s/var/cache/pacman/pkg"
            " && mkdir -m 0755 -p %s/var/lib/pacman"
            " && mkdir -m 0755 -p %s/var/log"
            " && mkdir -m 0755 -p %s/dev"
            " && mkdir -m 0755 -p %s/run"
            " && mkdir -m 0755 -p %s/etc"
            " && mkdir -m 1777 -p %s/tmp "
            " && mkdir -m 0555 -p %s/sys" 
            " && mkdir -m 0555 -p %s/proc", 
            _rootdir.c_str(), _rootdir.c_str(),
            _rootdir.c_str(), _rootdir.c_str(),
            _rootdir.c_str(), _rootdir.c_str(),
            _rootdir.c_str(), _rootdir.c_str(),
            _rootdir.c_str());
    
    if (system(buf) < 0) {
        cerr << string(buf) << " failed\n";
        return false;
    }

    snprintf(buf, sizeof buf - 1,
            "mount proc %s/proc -t proc -o nosuid,noexec,nodev &&"
            "mount sys %s/sys -t sysfs -o nosuid,noexec,nodev,ro &&"
            "mount udev %s/dev -t devtmpfs -o mode=0755,nosuid &&"
            "mount devpts %s/dev/pts -t devpts -o mode=0620,gid=5,nosuid,noexec &&"
            "mount shm %s/dev/shm -t tmpfs -o mode=1777,nosuid,nodev &&"
            "mount run %s/run -t tmpfs -o nosuid,nodev,mode=0755 &&"
            "mount tmp %s/tmp -t tmpfs -o mode=1777,strictatime,nodev,nosuid",
            _rootdir.c_str(), _rootdir.c_str(), _rootdir.c_str(), 
            _rootdir.c_str(), _rootdir.c_str(), _rootdir.c_str(), 
            _rootdir.c_str());

    if (system(buf) < 0) {
        cerr << string(buf) << " failed\n";
        return false;
    }

    snprintf(buf, sizeof buf - 1,
            "[[ -d '%s/sys/firmware/efi/efivars' ]] && "
            "mount efivarfs %s/sys/firmware/efi/efivars -t efivarfs -o nosuid,noexec,nodev",
            _rootdir.c_str(), _rootdir.c_str());
    if (system(buf) < 0) {
        cerr << string(buf) << " failed\n";
        return false;
    }

    return true;
}

bool AlpmInstaller::install(void (*progress)(int percent))
{
    _reporter = progress;

    PkgsMeta meta{"/PKGS/packages.install"};
    for(const auto& x: _groups) {
        cerr << "add group " << x << endl;
        for(const auto& s: meta(x)) {
            _targets = alpm_list_add(_targets, strdup(s.c_str()));
        }
    }

    int ret = ipacman_refresh_databases();
    ret += ipacman_sync_packages(_targets);

    if (_reporter)
        _reporter(100);
    return true;
}

void AlpmInstaller::collectPkgSize()
{
}

