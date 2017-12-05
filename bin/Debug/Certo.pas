program Prog1;
    var a : integer, b : integer;

    function Func1 (a : integer) : integer;
    var b : integer, d: integer;
    begin
        b = 2*a-1;

        while (b>0) do
        begin
            d = b;
            b = 2*d-1;
        end;
    end;

    procedure Proc1 (b : boolean);
    var a : boolean, c : boolean;
    begin
        if Func1(5) == 7 then begin
            a = true;
            c = not b;
        end;
        else begin
            a = not b;
            c = false;
        end;

        if (a and b or c) then
            write a;
        else
            write b;
    end;
begin
    a = 5;
    b = 7;

    while (a<b or (a>500 and b>700)) do
    begin
		Proc1(a < b);
        a = a + 2;
        b = 2 * b;
    end;

    write (a);
    write (b);
end;