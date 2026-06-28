int screen_point = 0;

void print_char(char c)
{
    volatile char *video_memory = (volatile char *)0xB8000;

    video_memory[screen_point * 2] = c;
    video_memory[screen_point * 2 + 1] = 0x07;

    screen_point++;
}

void print_string(char *str)
{
    int istr = 0;

    while (str[istr] != '\0')
    {
        print_char(str[istr]);
        istr++;
    }
}

void print_int(int inp)
{
    if (inp == 0)
    {
        print_char('0');
        return;
    }

    if (inp < 0)
    {
        print_char('-');
        return;
    }

    char buffer[12];
    int i = 0;

    while (inp > 0)
    {
        buffer[i] = (inp % 10) + '0';
        inp = inp / 10;
        i++;
    }

    for (int j = i - 1; j >= 0; j--)
    {
        print_char(buffer[j]);
    }
}

void print_float(float flt)
{
    if (flt < 0)
    {
        print_char('-');
        flt = -flt;
    }

    int integer_part = (int)flt;
    print_int(integer_part);

    print_char('.');

    float decimal_part = flt - (float)integer_part;

    int float_to_int = (int)(decimal_part * 10000.0f);

    if (float_to_int < 1000 && float_to_int > 0)
        print_char('0');
    if (float_to_int < 100 && float_to_int > 0)
        print_char('0');
    if (float_to_int < 10 && float_to_int > 0)
        print_char('0');

    if (float_to_int == 0)
    {
        print_string("0000");
    }
    else
    {
        print_int(float_to_int);
    }
}


//the man who you need;
void print(char *input, int num[], char *str[], char chr[], float flt[])
{
    int i = 0;

    int inum = 0;
    int istr = 0;
    int ichr = 0;
    int iflt = 0;

    while (input[i] != '\0')
    {

        if (input[i] == '%')
        {
            switch (input[i + 1])
            {
            case 'd':
            case 'i':
                print_int(num[inum]);
                inum++;
                break;
            case 'f':
                // this might break. be careful
                print_float(flt[iflt]);
                iflt++;
                break;
            case 'c':
                print_char(chr[ichr]);
                ichr++;
                break;
            case 's':
                print_string(str[istr]);
                istr++;
                break;
            }

            i += 2;
            continue;
        }
        print_char(input[i]);
        i++;
    }
}