#ifndef TEST_H
#define TEST_H


class Test
{
    public:
        Test();
        Test(unsigned int);
        ~Test();

        unsigned int GetCounter() { return _Counter; }
        void SetCounter(unsigned int val) { _Counter = val; }

    protected:

    private:
        unsigned int _Counter;
};

//PAS DE CODE ICI SAUF PROTOTYPE FONCTION

#endif // TEST_H
