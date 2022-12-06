void print_line()
{
    for (int i = 0; i < 80; i++)
    {
        printf("-");
    }

    printf("\n");
}

void clear_window()
{
#ifdef OS_Windows
    // Codigo Windows
    system("cls");

#else
    // Codigo GNU/Linux
    system("clear");
#endif
}

void pause()
{
#ifdef OS_Windows
    system("pause");
#else
    system("read");
#endif
}
