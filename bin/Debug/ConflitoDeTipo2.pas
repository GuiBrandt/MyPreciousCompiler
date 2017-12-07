program prog1;
    var a : integer, b: integer;

    procedure proc1 (b: boolean);
        var a: boolean, c: boolean;

        function func1 (var a: integer): integer;
        var b : integer, d: integer;
        begin
            b := 2*a-1;

            while (b>0) do
            begin
                d := b;
                b := 2*d-1;
            end;

            func1 := (b+d)/2;
        end;
    begin
        if (func1(5)/2 >7)
        then begin
            a := func1(4);
            c := not b;
        end
        else begin
            a := not b;
            c := false;
        end;

        if (a and b or c) then
            write 1;
        else
            write 2;
    end;
begin
    a := 5;
    b := 7;

    while (a<b || (a>500 && b>700)) do
    begin
        proc1(a<b);
        a := a+2;
        b := 2*b;
    end;

    write (a);
    write (b);
end.
