function arr2 = purge_outliers(arr)
    q1=quantile(arr,.05);
    q2=quantile(arr,.95);
    g=find((arr>q1)&(arr<q2));
    arr2 = arr(g);
end