int n;
binary_semaphore s = 1, delay = 0; void producer()
{
while (true) { produce();
                semWaitB(s);
                append();
                n++;
                if (n==1) semSignalB(delay);
                semSignalB(s);
} }
void consumer() {
int m; /* a local variable */ semWaitB(delay);
while (true) {
} }
void main() {
}
semWaitB(s);
take();
n--;
m = n;
semSignalB(s);
consume();
if (m==0) semWaitB(delay);
n = 0;
parbegin (producer, consumer);
