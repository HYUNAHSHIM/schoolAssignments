import sys


# for each point
# cluster_id = None (Not in cluster yet)
# cluster_id = -1 (Noise)
class Point:
    def __init__(self, p_id, x, y):
        self.p_id = p_id
        self.cluster_id = None
        self.visited = False
        self.x = x
        self.y = y


# get input information
def get_input(argv):
    in_file = argv[1]
    n = int(argv[2])
    eps = int(argv[3])
    min_pts = int(argv[4])
    # for output file name
    input_num = in_file[:6]
    # create object Point for each points
    points = []
    f = open(in_file, 'rt')
    for line in f.readlines():
        new_line = line.replace('\n', '').split('\t')
        points.append(Point(int(new_line[0]), float(new_line[1]), float(new_line[2])))
    f.close()
    return points, n, eps, min_pts, input_num


# calculate distance between two points p, q
def distance(p, q):
    return ((p.x - q.x) ** 2 + (p.y - q.y) ** 2) ** 0.5


# get neighbors by calculating distance
def get_neighbors(point_id, points, eps):
    neighbors = []
    for i in range(len(points)):
        # if distance of two points is not larger than eps, it is neighbor
        dist = distance(points[point_id], points[i])
        if dist <= eps:
            neighbors.append(i)
    return neighbors


# create new cluster with cluster_id
# add more neighbors in cluster
def create_cluster(points, neighbors, cluster_id, eps, min_pts):
    # check every neighbors to get new neighbors
    for neighbor in neighbors:
        points[neighbor].cluster = cluster_id
        # if already visited, skip
        if points[neighbor].visited:
            continue
        points[neighbor].visited = True
        # add more neighbors if neighbors' number is more than min_pts
        added_neighbors = get_neighbors(neighbor, points, eps)
        if len(added_neighbors) >= min_pts:
            neighbors.extend(added_neighbors)
    # if not in cluster, add to cluster
    for neighbor in neighbors:
        if points[neighbor].cluster_id is None:
            points[neighbor].cluster_id = cluster_id


# do dbscan
def dbscan(points, eps, min_pts):
    cluster_id = -1
    for i in range(len(points)):
        # skip if visited
        if points[i].visited:
            continue
        points[i].visited = True
        # get neighbors of point i
        neighbors = get_neighbors(i, points, eps)
        # if point is core point add new cluster
        if len(neighbors) >= min_pts:
            cluster_id += 1
            points[i].cluster_id = cluster_id
            create_cluster(points, neighbors, cluster_id, eps, min_pts)
        else:
            # else it is noise
            points[i].cluster_id = -1
    return points


# write data to output files
def write_output(out_file, points, n):
    files = []
    # output file name
    for i in range(n):
        files.append(open(out_file + '_cluster_' + str(i) + '.txt', 'wt'))
    # write each point's id in right cluster file
    for point in points:
        if point.cluster_id < n:
            files[point.cluster_id].write(str(point.p_id) + '\n')
    # close output files
    for i in range(n):
        files[i].close()


def main(argv):
    # get input information
    points, n, eps, min_pts, input_num = get_input(argv)
    # do dbscan
    points = dbscan(points, eps, min_pts)
    # write in output files
    write_output(input_num, points, n)


if __name__ == '__main__':
    main(sys.argv)
