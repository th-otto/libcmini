#include <stdlib.h>
#include <mint/osbind.h>
#include <sys/stat.h>

int stat(const char *path, struct stat *buff)
{
    _DTA *old_dta = Fgetdta();
	_DTA dta;
    long ret;

    Fsetdta(&dta);

    ret = Fsfirst(path, FA_DIR | FA_RDONLY | FA_HIDDEN | FA_SYSTEM);
    if (ret == 0)
    {
        buff->st_dev = (path[0] != '\0' && path[1] == ':') ? ((path[0] & ~0x20 /* toupper */) - 'A') : Dgetdrv();;
        buff->st_ino = 0;
        buff->st_mode = S_IRUSR;
        buff->st_nlink = 1;
        buff->st_uid = 0;
        buff->st_gid = 0;
        buff->st_rdev = buff->st_dev;
        buff->st_size = dta.dta_size;
        buff->st_atime = dta.dta_time;
        buff->st_mtime = dta.dta_time;
        buff->st_ctime = dta.dta_time;
    }

	Fsetdta(old_dta);

    return ret;
}

