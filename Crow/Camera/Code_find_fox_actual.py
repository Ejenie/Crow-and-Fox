import sensor, time, math, pyb
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQQVGA)

sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)

clock = time.clock()
serial = pyb.UART(3, 9600, timeout = 100, timeout_char = 100)
serial.init(9600, bits=8, parity=None, stop=1, timeout_char=100)
thresholds_first = [(47, 86, 13, 90, 7, 102)
]
lmin = [i for i in range(thresholds_first[0][0]+1)]
lmax = [i for i in range(thresholds_first[0][0], thresholds_first[0][1]+1)]
thresholds_now = [(lmin[i], 86, 13, 90, 7, 102) for i in range(len(lmin))]
thresholds_now+=[(lmax[i], 86, 13, 90, 7, 102)for i in range(len(lmax))]
print(*lmin)
print(*lmax)

img = sensor.snapshot()
w = img.width()
h  = img.height()
print(w, h)

while True:
    clock.tick()
    img = sensor.snapshot()
    mxBlob_first = None
    mxBlob_second = None
    mxBlob_fird = None
    centre = 90

    centre_servo = 0
    for blob in img.find_blobs(
        thresholds_now, roi = (0, h*2//3,  w, h),
        pixels_threshold = 100,
        area_threshold = 100,
        merge = True
    ):
        if mxBlob_first == None:
            mxBlob_first = blob
        if mxBlob_first.pixels() < blob.pixels():
            mxBlob_first = blob
    if mxBlob_first != None:
        img.draw_cross(mxBlob_first.cx(), mxBlob_first.cy(), size = 5, color = (255,0,0), thickness = 5)
        x = mxBlob_first.cx()
        serial.writechar(x)
        print(x)
