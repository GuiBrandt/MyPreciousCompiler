Program Prog1;
    Var a : Integer, b: Integer;

    Procedure Proc1 (b: Boolean);
        Var a : Boolean, c: Boolean;

        Function Func1 (a: Integer): Integer;
            Var b: Integer, d: Integer;
        Begin
            b := 2*a-1;

            While (b>0) Do
            Begin
                d := b;
                b := 2*d-1;
            End;

            Func1 := (b+d)/2;
        End;
    Begin
        If (Func1(5)/2 >7)
        Then Begin
            a := true;
            c := not b;
        End
        Else Begin
            a := not b;
            c := false;
        End;

        If (a and b or c)
            Write 1
        Else
            Write 2;
    End;
Begin
    1a := 5;
    b := 7;

    While (a<b || (a>500 && b>700)) Do
    Begin
        Proc1(a<b);
        a := a+2;
        b := 2*b;
    End;

    Write (a);
    Write (b);
End.