/* program diningphilosophers */ semaphore fork [5] = {1};
int i;
void philosopher (int i)
{
}
     while (true) {
think();
wait (fork[i]);
wait (fork [(i+1) mod 5]); eat();
signal(fork [(i+1) mod 5]); signal(fork[i]);
}
void main()
{
parbegin (philosopher (0), philosopher (1), philosopher (2), philosopher (3), philosopher (4));
}

//or

semaphore fork[5] = {1}; semaphore room = {4};
int i;
void philosopher (int i) {
     while (true) {
think();
wait (room);
wait (fork[i]);
wait (fork [(i+1) mod 5]); eat();
signal (fork [(i+1) mod 5]); signal (fork[i]);
signal (room);
} }
void main() {
  parbegin (philosopher (0), philosopher (1), philosopher (2), philosopher (3), philosopher (4));
}
