int main(void)
{
    int ABtoC[2];
    pipe(ABtoC);

    if (fork() > 0)
    {
        // Process A
        close(ABtoC[0]);
        dup2(ABtoC[1], STDOUT_FILENO);
        close(ABtoC[1]);     // Close this too!
        // Process A writing to C
        for (int i = 0; i < 100; i++)
        {
            write(STDOUT_FILENO, "Hi\n", sizeof("Hi\n")-1);
            usleep(5000);
        }
    }
    else if (fork() > 0)
    {
        // Process B
        close(ABtoC[0]);
        dup2(ABtoC[1], STDOUT_FILENO);
        close(ABtoC[1]);
        // Process B writing to C
        for (int i = 0; i < 100; i++)
        {
            write(STDOUT_FILENO, "Lo\n", sizeof("Lo\n")-1);
            usleep(5000);
        }
    }
    else
    {
        char buffer[100];
        ssize_t nbytes;
        close(ABtoC[1]);
        dup2(ABtoC[0], STDIN_FILENO);
        close(ABtoC[0]);
        // Process C reading from both A and B
        while ((nbytes = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
            write(STDOUT_FILENO, buffer, nbytes);
    }
    return(0);
}