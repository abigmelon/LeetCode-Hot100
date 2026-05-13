

long long gcd(long long a, long long b){
    while(b != 0){
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main(){
    long long a, b, c, k;
    while(scanf("%lld %lld %lld %lld", &a, &b, &c, &k) == 4){
        if(a == 0 && b == 0 && c == 0 && k == 0) break;
        if(a == b){
            printf("0\n");
            continue;
        }
        if(c == 0){
            printf("FOREVER\n");
            continue;
        }
        long long m = 1LL << k;
        long long aim = ((b - a) % m + m) % m;
        long long d = gcd(c, m);
        if(aim % d != 0){
            printf("FOREVER\n");
            continue;
        }
        long long c1 = c / d;
        long long target = aim / d;
        long long m1 = m / d;
        for(long long n = 0; n < m; n++){
            if((c1 * n) % m1 == target){
                printf("%lld\n", n);
                break;
            }
        }
    }
    return 0;
}