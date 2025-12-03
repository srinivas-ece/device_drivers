
#include <linux/ioctl.h>
#define BUF_LEN 256

#define serial_magic 's'
#define serial_reset	_IO(serial_magic,0)
#define CMD_SET_MGS    _IOW(serial_magic,1,char *)
#define CMD_TO_MGS    _IOR(serial_magic,2,char *)




