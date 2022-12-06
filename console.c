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
    system("cls");

#else
    system("clear");
#endif
}

void pause_console()
{
#ifdef OS_Windows
    system("pause");
#else
    system("read");
#endif
}
