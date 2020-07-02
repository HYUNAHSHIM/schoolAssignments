import sys
import itertools


# generate candidate with length '1'
def create_first_candidate():
    tmp_pat = dict()
    for tran in trans:
        for item in tran:
            # if item is already in tmp_pat
            if item in tmp_pat.keys():
                tmp_pat[item] += 1
            # if item is not in tmp_pat add new one
            else:
                tmp_pat[item] = 1
    return generate_ln(tmp_pat)


# delete candidate if it's support is smaller than minimum support
def generate_ln(candidate):
    tmp_pat = dict()
    min_sup_cnt = min_sup * len(trans)
    for key in candidate.keys():
        # if support of candidate is smaller than minimum support delete
        if candidate[key] >= min_sup_cnt:
            tmp_pat[key] = candidate[key]
    # if there's no more candidate exit
    if len(tmp_pat) < 1:
        exit()
    return tmp_pat


# make input to list(set(...))
def list_to_set(pattern):
    tmp_list = list()
    for item in pattern:
        tmp_list.append(set(item))
    return tmp_list


# self Joining and pruning to generate new candidate with length k+!
def generate_candidate(k_pattern, pat_length):
    # self joining
    candidate = list()
    # if previous candidate's length is 1, combination
    if pat_length == 2:
        candidate = list_to_set(list(itertools.combinations(k_pattern, pat_length)))
    # if previous candidate's length is larger than 1,
    else:
        for first_list in k_pattern:
            for second_list in k_pattern:
                if first_list == second_list:
                    continue
                # if list union's length is pat_length join
                first_list = set(first_list)
                second_list = set(second_list)
                tmp = first_list | second_list
                if len(tmp) == pat_length:
                    candidate.append(tmp)
    # check if candidate exists
    if len(candidate) == 0:
        exit()
    # pruning
    # change kth frequent pattern list to set
    if pat_length == 2:
        tmp = list()
        for item in k_pattern:
            tmp.append(set([item, ]))
        k_pattern = tmp
    else:
        k_pattern = list_to_set(k_pattern)
    # Downward closure property
    result = dict()
    for items in candidate:
        cnt = 0
        for item in list(itertools.combinations(items, pat_length - 1)):
            item = set(item)
            # if there's pattern that is not in k-th frequent pattern delete
            if item not in k_pattern:
                break;
            cnt += 1
        # if every combination is in k-th frequent pattern, make this pattern k+1th frequent pattern
        if cnt == pat_length:
            # list or set cannot be key of dic type
            result[tuple(items)] = 0
    # scan DB for count frequency
    for key in result.keys():
        for tran in trans:
            if set(key) <= set(tran):
                result[key] += 1
    return generate_ln(result)


# apply association rule and then write to output.txt
def association_rule(pat_length, candidate):
    for items, frequency in candidate.items():
        tmp_len = pat_length
        # divide patterns to item set and associative item set
        while tmp_len > 1:
            union = list(list_to_set(itertools.combinations(items, tmp_len - 1)))
            for item in union:
                # get associative item set
                ass_item_set = set(items) - set(item)
                support = frequency / len(trans) * 100
                item_num = 0
                # count number of items in transaction to get confidence
                for tran in trans:
                    if set(tran) >= item:
                        item_num += 1
                confidence = frequency / item_num * 100
                # to delete '' at output file
                item = set(map(int, item))
                ass_item_set = set(map(int, ass_item_set))
                result = str(item) + '\t' + \
                         str(ass_item_set) + '\t' + \
                         str('%.2f' % round(support, 2)) + '\t' + \
                         str('%.2f' % round(confidence, 2)) + '\n'
                # write result
                with open(sys.argv[3], 'a') as out:
                    out.write(result)
            tmp_len -= 1


# main function
if __name__ == '__main__':
    # list for saving transactions
    trans = list()
    # get data from input.txt
    argv = sys.argv
    min_sup = float(argv[1]) / 100
    outfile = argv[3]
    with open(sys.argv[2], 'r') as infile:
        data = infile.read().split('\n')
        for trx in data:
            trx = trx.split('\t')
            trans.append(trx)
    # list that stores frequent patterns
    freq_pat = list()
    # generate the first Candidate with length 1 and append it to freqPat list
    freq_pat.append(create_first_candidate())
    length = 2
    while True:
        # get the length-k frequent pattern, which is L(k)
        k_freq_pat = list(freq_pat[length - 2].keys())
        print(str(length - 1) + "-th frequent pattern : " + str(k_freq_pat))
        # generate Candidate by self-joining and pruning, return the L(k+1)
        next_can = generate_candidate(k_freq_pat, length)
        # if there's any candidate exit
        if next_can == -1:
            exit()
        # apply association Rule and write in output.txt
        association_rule(length, next_can)
        # add length-(k+1) frequent pattern to freqPat, and then length++ for k+2 frequent pattern
        freq_pat.append(next_can)
        length += 1
