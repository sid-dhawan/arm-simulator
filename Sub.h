class Sub
{
    private:
        long op1, op2, res, des;
        void Execute();
        void Memory();
        void Write-back();
    public:
        Sub(long des, long op1, long op2);
};