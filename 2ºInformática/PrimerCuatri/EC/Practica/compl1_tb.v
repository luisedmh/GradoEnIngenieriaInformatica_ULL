`timescale 1ns / 10ps

module tb_compl1;

    reg [3:0] Inp;        
    reg cpl;              
    wire [3:0] Out;       


    compl1 uut (
        .Out(Out),
        .Inp(Inp),
        .cpl(cpl)
    );

    initial begin

        $dumpfile("tb_compl1.vcd");
        $dumpvars(0, tb_compl1);

        $monitor("Time=%0t | Inp=%b | cpl=%b | Out=%b", $time, Inp, cpl, Out);

        Inp = 4'b0101; cpl = 0;
        #10; 


        Inp = 4'b0101; cpl = 1;
        #10;

        Inp = 4'b1111; cpl = 0;
        #10;

        Inp = 4'b1111; cpl = 1;
        #10;

        Inp = 4'b0000; cpl = 0;
        #10;

        Inp = 4'b0000; cpl = 1;
        #10;

        $finish;
    end
endmodule
