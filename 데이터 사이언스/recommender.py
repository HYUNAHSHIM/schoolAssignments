import sys


# get input information
def get_input(argv):
    train_file = open(argv[1], 'rt')
    test_file = open(argv[2], 'rt')
    res_file = argv[1] + '_prediction.txt'
    train_data = {}
    test_data = []
    # get data to dictionary type
    for line in train_file:
        new_line = line.replace('\n', '').split('\t')
        if int(new_line[0]) in train_data.keys():
            train_data[int(new_line[0])][int(new_line[1])] = int(new_line[2])
        else:
            train_data[int(new_line[0])] = {int(new_line[1]): int(new_line[2])}
    for line in test_file:
        new_line = line.replace('\n', '').split('\t')
        test_data.append(new_line)
    train_file.close()
    test_file.close()
    return train_data, test_data, res_file


# calculate average rating of each user
def calculate_average(train_data):
    average_rating = {}
    for key in train_data.keys():
        for rating in train_data[key].keys():
            if key in average_rating:
                average_rating[key] += train_data[key][rating]
            else:
                average_rating[key] = train_data[key][rating]
        average_rating[key] /= len(train_data[key].keys())
    return average_rating


# get common items of user1 and user2
def get_common_items(user1, user2, train_data):
    common_items = []
    for item in train_data[user1].keys():
        if item in train_data[user2].keys():
            common_items.append(item)
    return common_items


# use pearson correlation coefficient to get similarity
# return to matrix
def calculate_pearson(train_data, average_rating):
    user_num = len(train_data.keys())
    matrix = [[] for i in range(user_num + 1)]
    for i in range(1, user_num + 1):
        matrix[i] += [0 for j in range(user_num + 1)]
    for user1 in range(1, user_num + 1):
        for user2 in range(1, user1):
            # numerator
            up = 0
            # denominator
            under1 = 0
            under2 = 0
            common_items = get_common_items(user1, user2, train_data)
            # if there's no common items
            if len(common_items) == 0:
                matrix[user1][user2] = 0
                matrix[user2][user1] = 0
            else:
                # if there's common items, calculate pearson correlation coefficient
                for item in common_items:
                    up += (train_data[user1][item] - average_rating[user1])\
                            * (train_data[user2][item] - average_rating[user2])
                    under1 += ((train_data[user1][item] - average_rating[user1]) ** 2)
                    under2 += ((train_data[user2][item] - average_rating[user2]) ** 2)
                if under1 == 0 or under2 == 0:
                    similarity = 0
                else:
                    similarity = up / ((under1 * under2) ** 0.5)
                matrix[user1][user2] = similarity
                matrix[user2][user1] = similarity
    return matrix


# get neighbors who's pearson correlation coefficient is (+)
def get_neighbors(matrix, user):
    neighbors = []
    user_matrix = matrix[user]
    for i in range(len(user_matrix)):
        if user_matrix[i] > 0:
            neighbors.append(i)
    return neighbors


# calculate recommend rating
def recommend(train_data, average_rating, matrix, user, item):
    predict_rating = -1
    normalize = 0
    weighted_sum = 0
    have_neighbor_value = False
    k = 60
    neighbors = get_neighbors(matrix, user)
    # if there's no similar user
    if len(neighbors) != 0:
        for neighbor in neighbors:
            if item not in train_data[neighbor].keys():
                continue
            have_neighbor_value = True
            weight = matrix[user][neighbor]
            normalize += weight
            weighted_sum += weight * (train_data[neighbor][item] - average_rating[neighbor])
            k -= 1
            if k == 0:
                break
    if len(neighbors) == 0 or have_neighbor_value == False:
        predict_rating = 0
    else:
        predict_rating = average_rating[user]
        predict_rating += (weighted_sum / normalize)
    if predict_rating > 5:
        return 5
    elif predict_rating < 1:
        return 1
    else:
        return round(predict_rating)


def main(argv):
    # get input data
    train_data, test_data, res_file = get_input(argv)
    # calculate average of rating
    average_rating = calculate_average(train_data)
    # use pearson correlation coefficient
    correlation_matrix = calculate_pearson(train_data, average_rating)
    # write the result
    out_file = open(res_file, 'wt')
    for test in test_data:
        result = recommend(train_data, average_rating, correlation_matrix, int(test[0]), int(test[1]))
        out_file.write(str(test[0]) + '\t' + str(test[1]) + '\t' + str(int(result)) + '\n')
    out_file.close()


if __name__ == '__main__':
    main(sys.argv)
