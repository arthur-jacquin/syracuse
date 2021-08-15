long f (long n) {
    if (n & 1) {
        return 3*n + 1;
    } else {
        return n >> 1;
    };
};

long m (long n) {
    int res = 0;
    while (n >> 1) {
        n = f(n);
        res++;
    };
    return res;
};
