import sys
import math

samples = {}


# get data from train_file and test_file
def get_data(train_file, test_file):
    train = open(train_file, 'rt', encoding='utf-8')

    # get attribute name
    first = train.readline()
    attribute = first.replace('\n', '').split('\t')

    # get training data set
    train_set = [line.replace('\n', '').split('\t') for line in train.readlines()]
    train.close()

    # get test data set
    test = open(test_file, 'rt', encoding='utf-8')
    # first line is attribute name so remove
    test.readline()
    test_set = [line.replace('\n', '').split('\t') for line in test.readlines()]
    test.close()
    return train_set, test_set, attribute


# count the number of each class labels
def count_label(class_label):
    cnt = {}
    for label in class_label:
        if label in cnt.keys():
            cnt[label] += 1
        # if there's no label add to dict
        else:
            cnt[label] = 0
    return cnt


# return value is data set who's attribute is label
def partition_data(train_set, attribute, label):
    # ex) train_set = [['>30', 'yes'], ['<30', 'no]]
    # ex) attribute = 3
    # ex) label = '>30'
    partitioned_data_set = []

    # get training data who's attribute's label is argument 'label'
    for data in train_set:
        if data[attribute] == label:
            partitioned_data_set.append(data)
    return partitioned_data_set


# calculate Info(D)
def calculate_entropy(train_set):
    # check every labels of class label
    labels = {}
    for data in train_set:
        label = data[-1]
        if label not in labels.keys():
            labels[label] = 0
        labels[label] += 1
    # calculate Info(D)
    entropy = 0.0
    for label in labels:
        prob = float(labels[label]) / len(train_set)
        entropy += (-1) * prob * math.log(prob, 2)
    return entropy


# calculate information gain of each attributes
def information_gain(train_set, attribute):
    max_info_gain = 0.0
    best_attribute = 0
    best_attribute_label = {}

    # calculate original entropy
    origin_entropy = calculate_entropy(train_set[:])

    # calculate entropy for every attribute
    num_attribute = len(attribute)
    for i in range(num_attribute):
        entropy = 0.0
        # get every labels of this attribute using 'set'
        labels = [data[i] for data in train_set]
        labels = set(labels)

        # calculate Info(D) of attribute(i)
        for label in labels:
            # i is order of attribute
            partitioned_data = partition_data(train_set[:], i, label)
            prob = float(len(partitioned_data)) / (len(train_set))
            entropy += (prob * calculate_entropy(partitioned_data[:]))

        # calculate information gain and get the max information gain which is best attribute
        info_gain = origin_entropy - entropy
        if info_gain > max_info_gain:
            max_info_gain = info_gain
            best_attribute = i
            best_attribute_label = labels
    return best_attribute, list(best_attribute_label)


# create tree recursively
def create_tree(train_set, attribute):
    global samples
    # ex) train_set = [[1, 2, 'yes'(this is class label)], [1, 0, 'no']]
    # ex) attribute = ['age' , 'student']

    # if every class label of tuples are same, stop partitioning
    class_label = [data[-1] for data in train_set]
    if len(class_label) == class_label.count(class_label[0]):
        return [class_label[0]]
    # if there's no more attributes for partitioning, stop and return the class label which is most frequent
    # 1 is left for class label
    partitioned_class_label = count_label(class_label)
    if len(train_set[0]) == 1:
        freq_label = ''
        frequency = 0
        for label in partitioned_class_label.keys():
            if partitioned_class_label[label] > frequency:
                frequency = partitioned_class_label[label]
                freq_label = label
        return [freq_label]

    # select best attribute by information_gain
    # last element of attribute is class label so remove
    best_attribute, labels = information_gain(train_set[:], attribute[:-1])

    # remove used attribute
    best_attribute_str = attribute.pop(best_attribute)

    # split training data set by selected attribute
    label_dict = {}
    tree = {}

    for label in labels:
        tmp_data = partition_data(train_set[:], best_attribute, label)
        partitioned_data = []
        for tmp in tmp_data:
            tmp.pop(best_attribute)
            partitioned_data.append(tmp)
            if tmp in train_set:
                index = train_set.index(tmp)
                train_set.pop(index)
        label_dict[label] = create_tree(partitioned_data[:], attribute[:])
    tree[best_attribute_str] = label_dict
    samples[best_attribute_str] = partitioned_class_label
    return tree


def test_model(tree, data, attribute):
    global samples
    # ex) data = ['<30', 'yes', 'no']
    # ex) attribute = ['age', 'student', 'buy computer']
    # ex) samples = {'age' : {'yes': 15, 'no': 20}, ...}
    # ex) tree = {'age':{'>30' : {'student' :{..}}}}
    subtree = {}
    for key in tree:
        # index of attribute
        index = attribute.index(key)
        # label of the attribute
        label = data[index]
        if label in tree[key]:
            subtree = tree[key][label]
        # if label not in tree, return the most frequent class label
        else:
            class_label = samples[key]
            freq_label = ''
            frequency = 0
            for i in class_label.keys():
                if class_label[i] > frequency:
                    freq_label = i
                    frequency = class_label[i]
            return freq_label
        # if end of tree
        if type(subtree) == list:
            return subtree[0]
    # if not end of tree repeat recursively
    return test_model(subtree, data, attribute)


# main function
def main(argv):
    # get the file names from arguments
    train_file = argv[1]
    test_file = argv[2]
    result_file = argv[3]
    # get data of training set, test set and attribute name
    train_set, test_set, attribute = get_data(train_file, test_file)
    # create tree using training set
    tmp_att = attribute[:]
    # create tree
    tree = create_tree(train_set, attribute)

    # evaluate model with test data set
    results = [tmp_att]

    # ex) result = [['age', 'buy', 'label'], [1, 0, 'yes'], [2, 1, 'no']]
    for data in test_set:
        label = [test_model(tree, data, tmp_att)]
        results.append(data + label)

    # write result in result_file
    file = open(result_file, 'wt', encoding='utf-8')
    for result in results:
        for i in range(len(result) - 2):
            file.write(result[i] + '\t')
        file.write(str(result[-1]) + '\n')
    file.close()


if __name__ == '__main__':
    main(sys.argv)
