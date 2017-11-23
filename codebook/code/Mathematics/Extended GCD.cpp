template <typename T>
T extgcd(T a, T b, T &x, T &y){ 
    // g = a * x + b * y
    T g = a; 
    if (b != 0) { 
        g = extgcd(b, a % b, y, x); 
        y -= (a / b) * x; 
    } 
    else x = 1, y = 0; 
    return g;
}