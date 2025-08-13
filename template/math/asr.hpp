using myfloat = double;

myfloat simpson(myfloat l, myfloat r, auto&& f)
{
    myfloat mid = (l + r) / 2;
    return (r - l) * (f(l) + myfloat(4) * f(mid) + f(r)) / 6;  // 辛普森公式
}

myfloat asr(myfloat l, myfloat r, myfloat eps, myfloat ans, int step, auto&& f)
{
    myfloat mid = (l + r) / 2;
    myfloat fl = simpson(l, mid, f), fr = simpson(mid, r, f);
    if (abs(fl + fr - ans) <= 15 * eps && step < 0) return fl + fr + (fl + fr - ans) / 15;  // 足够相似的话就直接返回
    return asr(l, mid, eps / 2, fl, step - 1, f) + asr(mid, r, eps / 2, fr, step - 1, f);   // 否则分割成两段递归求解
}

myfloat calc(myfloat l, myfloat r, myfloat eps, auto&& f)
{
    return asr(l, r, eps, simpson(l, r, f), 2, f);
}
