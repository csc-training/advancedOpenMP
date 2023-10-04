# map alloc map type



Use the map clause to only allocate x for temporary use on the device.
Compile and run `map_alloc(.cpp|.F90)`.

1.) Look over the code.
    It uses x on the device, but needs no data transfer.
    Map x with the "alloc" map type to avoid any data
    transfer between original and corresponding data storage.

    Yes, it is a very contrived example.
    See OpenMP Examples document for more involved examples.
    Was it necessary to explictly map y?

```
./a.out
```
