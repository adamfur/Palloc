# Palloc

C treats the memory as one continious array. Writing outside your boundary might, but probably won't alert you of any missconduct.
```c
ptr = (char *) malloc(42);

*(ptr + 41) = '\0'; // OK: Last element in the memory region.
*(ptr + 42) = '\0'; // **BAD**: Outside allowed memory boundary. Silently corrupting memory!!!
```

However with palloc, allocation will yield a memory map, strictly followed by a nonwriteable region.
```c
ptr = (char *) palloc(42);

*(ptr + 41) = '\0'; // OK: Last element in the memory region.
*(ptr + 42) = '\0'; // Will always SEGFAULT!
```