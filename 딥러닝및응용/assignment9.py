import tensorflow as tf
import numpy as np

tf.set_random_seed(777) # reproducibility

# one hot encoding 정의
sample = " if you want you"
idx2char = list(set(sample)) # index -> char, list화
char2idx = {c: i for i, c in enumerate(idx2char)} # char -> idex, ex) {'k': 0, 'e': 1, ' ': 2, 'I': 3, 'u': 4, 'm': 5, 'y': 6, 'l': 7, 'i': 8, 'o': 9}

# hyper parameters
dic_size = len(char2idx) # RNN input size (one hot size)
hidden_size = len(char2idx) # RNN output size
num_classes = len(char2idx) # final output size (RNN or softmax, etc.)
batch_size = 1 # one sample data, one batch
sequence_length = len(sample) - 1 # number of lstm rollings (unit #)
learning_rate = 0.1

# one hot encoding 구현
sample_idx = [char2idx[c] for c in sample] # char to index, ex) [3, 2, 7, 8, 0, 1, 2, 6, 9, 4, 2, 5, 1]
x_data = [sample_idx[:-1]] # X data sample (0 ~ n-1) hello: hell
y_data = [sample_idx[1:]] # Y label sample (1 ~ n) hello: ello

#####
num = np.unique(x_data, axis=0)
encoding = np.eye(dic_size)[x_data]
x_data = np.array([encoding], dtype=np.float32)
    
X = tf.placeholder(tf.float32, [None, sequence_length, hidden_size])
Y = tf.placeholder(tf.int32, [None, sequence_length])

cell = tf.contrib.rnn.BasicRNNCell(num_units = hidden_size)
outputs, _state = tf.nn.dynamic_rnn(cell, X, dtype=tf.float32)
#####

# FC layer
X_for_fc = tf.reshape(outputs, [-1, hidden_size])
outputs = tf.contrib.layers.fully_connected(X_for_fc, num_classes, activation_fn=None)

# reshape out for sequence_loss
outputs = tf.reshape(outputs, [batch_size, sequence_length, num_classes])

weights = tf.ones([batch_size, sequence_length])
sequence_loss = tf.contrib.seq2seq.sequence_loss(logits=outputs, targets=Y, weights=weights)
loss = tf.reduce_mean(sequence_loss)
train = tf.train.AdamOptimizer(learning_rate = learning_rate).minimize(loss)

prediction = tf.argmax(outputs, axis=2)

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    for i in range(50):
        l, _ = sess.run([loss, train], feed_dict={X: x_data, Y: y_data})
        result = sess.run(prediction, feed_dict={X: x_data})
        
        # print char using dic
        result_str = [idx2char[c] for c in np.squeeze(result)]
        print(i, "loss:", l, "Prediction:", ''.join(result_str))
