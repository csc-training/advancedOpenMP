# declare mapper directive

The declare mapper can be used to prescribe a data
map to be used later use.  It is restricted for use with 
structures(C/C++), classes(C++) and derived types(F).

In the following example the
mapper specifies that the structure of type myvect_t
and the storage for its pointer "data" are to
be mapped (tofrom,default) when a variable of this
type is identified (used) within a target construct.

Any valid base-language variable (here, v) can be
used to reference elements within the map clause.

1.) Look over the code, mapper1(.cpp | .F0).

    C
    After the definition of the structure myvec_t
    use the declare mapper directive to define the
    default mapping for a structure of this type,
    a map for the structure, and the array section of
    data with a size specified with the structure 
    element "len".
    TODO 1:

    Fortran
    After the definition of the derived type  myvec_t
    is included in the main program by "use my_structures",
    use the declare mapper directive to define the
    default mapping for a variable of this derived type,
    and a map for the derived type, and and an
    array section with the size from the "len" element.
    TODO 1:

    Unfortunately, the CCE 15.0.1 compiler has an internal
    error when it compiles the Fortran code-- This has
    been fixed in 16.0, but is not yet available for LUMI.

    Compile and run.

2.) Look over the code, mapper2(.cpp | .F90).
    C
    a.) After the definition of the structure v_t
        use the declare mapper directive to define the
        default mapping for a structure of this type,
           with an identifier left_id
        a map for the structure, and the array section of
        data with a size N/2.  //TODO 2a.

    b.) On the target construct use the left_id with
        a mapper modifier and a map type of from. //TODO 2b

    Fortran
    a.) After the definition of the derived type (DT) v_t
        use the declare mapper directive to define the
        default mapping for a DT of this type,
           with an identifier left_id
        a map for the derived type, and the array section of
        data with a size N/2. !! TODO 2a

    b.) On the target construct specify the left_id identifier 
        for the my_vec DT with a mapper modifier and a 
        map type of from.  !!TODO 2b:
