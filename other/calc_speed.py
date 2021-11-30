# import nampy as np


def main():
    print('Input pulse time (Low time + Hight time).')
    print('Examples: 10298, 20596, 41192, etc...')
    t_time = input('Input number(ms): ')# micro second

    print('-- Preference --')
    # setting
    wheelSize = 0.51  # meter
    print('Wheel Size(m): ', wheelSize)

    wheelCircumference = wheelSize * 3.14  # meter
    print('Wheel Circumference(m): ', wheelCircumference)

    pulse = 48      # pulse
    print('Pulse(count): ', pulse)

    # t_time = 20596  
    # t_time = 10298
    # t_time = 41192
    
    print('-- Result --')
    frec = (1000000/float(t_time))  # Hz
    print('Pulse Frequence(Hz): ', frec)

    rotate = frec / 48
    print('Rotate Count(Count/s): ', rotate)

    runDist = rotate * wheelCircumference
    print('Run Distance(m): ', runDist)

if __name__ == '__main__':
    main()