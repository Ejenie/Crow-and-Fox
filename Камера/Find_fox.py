import sensor, time, math, pyb

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
clock = time.clock()

thresholds_first = [
    (20, 100, 3, 88, 21, 127)     #fox
]
lmin = [i for i in range(thresholds_first[0][0]+1)]
lmax = [i for i in range(thresholds_first[0][0], thresholds_first[0][1]+1)]
thresholds_now = [(lmin[i], 100, 3, 88, 21, 127) for i in range(len(lmin))]
thresholds_now+=[(lmax[i], 100, 3, 88, 21, 127) for i in range(len(lmax))]

print(*lmin)
print(*lmax)
green_led = pyb.LED(2)
blue_led = pyb.LED(3)

s1 = pyb.Servo(1)   # create a servo object on position P7

img = sensor.snapshot()
w = img.width()
h = img.height()

while True:

    s1.angle(45)
    clock.tick()
    img = sensor.snapshot()
    mxBlob_first = None
    mxBlob_second = None
    mxBlob_fird = None
    centre = w//2

    #find orange object
    for blob in img.find_blobs(
        thresholds_now, roi = (0, 0, w, h),
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
        print(mxBlob_first.cx(), mxBlob_first.cy())
        x = mxBlob_first.cx()
        if x < centre:
            x = -x
        s1.angle(x)
    #print(clock.fps())
