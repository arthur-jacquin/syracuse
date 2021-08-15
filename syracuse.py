l = 64 # Nombre de bit maximal

def to_bits(n):
    ''' Decomposition binaire (poids des bits croissant) '''
    return [(n >> i)%2 for i in range(l)]

def ADDr(in1, in2, in3):
    ''' Retourne les bits de in1 + in2 + in3 '''
    out2, out1 = divmod(in1 + in2 + in3, 2)
    return out1, out2

def iter_impair(bits):
    ''' Retourne la prochaine iteration impaire de n (impair) '''
    
    # Bits
    in1 = 1
    in2 = 1
    out = 0

    # Long
    nb_iter = 2
    max_bit = -1
    k = -1
    
    # Resultat
    res = [0]*l

    # Generation
    for i in range(l):
        (out, in1), in2 = ADDr(in1, in2, bits[i]), bits[i]
        if k == -1:
            if out == 0:
                nb_iter += 1
            else:
                k = 0
        else:
            if out == 1:
                max_bit = k
                res[k] = 1
            k += 1

    out, in1 = ADDr(in1, in2, 0)
    if out == 1:
        max_bit = k
        res[k] = 1
    
    # Detection d'overflow
    if in1 == 1:
        max_bit = l
    
    # Resultat
    return res, nb_iter, max_bit + 1

def m(n):
    assert n > 0 # Verification n non nul

    res = 0
    i = n
    while i%2 == 0:
        res += 1
        i >>= 1
    # i contient n/2^Val2(n) donc est impair
    if i == 1:
        return res
    if i >> l + 1: # Nombre non represente par l bits
        return 0
    i_bits = to_bits(i >> 1) # Transformation en bits
    while True:
        i_bits, nb_iter, taille = iter_impair(i_bits)
        res += nb_iter
        if taille == l + 1:
            return 0 # Correspond a un overflow
        elif taille == 0:
            return res # 1 est atteint !

for i in range(1, 101):
    print(m(i))
