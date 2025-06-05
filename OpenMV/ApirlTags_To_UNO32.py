import sensor
import time
import math
import pyb
from pyb import UART

# 相机设置
sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(time=2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)

clock = time.clock()
f_x = (2.8 / 3.984) * 320
f_y = (2.8 / 2.952) * 240
c_x = 160
c_y = 120

# 串口设置
uart = UART(3, 115200, timeout_char=200)

# 上次发送的Tag信息
last_sent_id = -2
last_Tx = 0
last_Tz = 0
last_Ry = 0

# 丢失检测
lost_counter = 0
max_lost = 5

# 定义角度转换函数
def degrees(rad):
    return (180 * rad) / math.pi

while True:
    clock.tick()
    img = sensor.snapshot()
    tag_found = False

    for tag in img.find_apriltags(fx=f_x, fy=f_y, cx=c_x, cy=c_y):
        tag_found = True
        lost_counter = 0
        pyb.LED(3).off()

        tag_id = tag.id
        Tx = int(tag.x_translation * 10)
        Ty = int(tag.y_translation * 10)
        Tz = int(tag.z_translation * 10)
        Rx = int(degrees(tag.x_rotation))
        Ry = int(degrees(tag.y_rotation))
        Rz = int(degrees(tag.z_rotation))

        # 只有在tx、tz、ry有显著变化时才发送
        if (tag_id != last_sent_id or
            abs(Tx - last_Tx) > 3 or
            abs(Tz - last_Tz) > 3 or
            abs(Ry - last_Ry) > 3):

            msg = "%d,%d,%d,%d,%d,%d,%d\r\n" % (tag_id, Tx, Ty, Tz, Rx, Ry, Rz)
            uart.write(msg)

            last_sent_id = tag_id
            last_Tx = Tx
            last_Tz = Tz
            last_Ry = Ry

        break  # 只处理第一个检测到的Tag

    if not tag_found:
        lost_counter += 1
        if lost_counter >= max_lost:
            pyb.LED(3).on()
            if last_sent_id != -1:
                uart.write("-1,0,0,0,0,0,0\r\n")
                last_sent_id = -1
            lost_counter = max_lost
