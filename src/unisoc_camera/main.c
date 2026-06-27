#include <linux/fs.h>
#include <linux/uaccess.h>

#define SENSOR_IOCTL_SET_FLIP    _IOW('s', 25, unsigned int)

long (*orig_sprd_sensor_file_ioctl)(struct file *file, unsigned int cmd, unsigned long arg);

long my_sprd_sensor_file_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    if (cmd == SENSOR_IOCTL_SET_FLIP) {
        unsigned int forced_orientation = 3; // 3 = Both H-Flip and V-Flip (180° rotation)
        arg = (unsigned long)&forced_orientation;
    }
    return orig_sprd_sensor_file_ioctl(file, cmd, arg);
}

KP_HOOK(sprd_sensor_file_ioctl, my_sprd_sensor_file_ioctl, &orig_sprd_sensor_file_ioctl);
