import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt
import os

# to ignore computer error
os.environ['KMP_DUPLICATE_LIB_OK'] = 'True'

from tensorflow.examples.tutorials.mnist import input_data

mnist = input_data.read_data_sets("./mnist/data/", one_hot=True)

# 한 스텝당 얼마나 학습시킬지
batch_size = 100
# 학습 반영률
learning_rate = 0.01
# 현재 data를 얼마나 반복할지
epoch_num = 20
# MNIST image data 차원
n_input = 28 * 28
# input data를 얼마의 차원으로 바꿀것인가
n_hidden1 = 256
n_hidden2 = 128

X = tf.placeholder(tf.float32, [None, n_input])

W_encode1 = tf.Variable(tf.random_uniform([n_input, n_hidden1], -1., 1.))
b_encode1 = tf.Variable(tf.random_uniform([n_hidden1], -1., 1.))

encoder_h1 = tf.nn.sigmoid(tf.add(tf.matmul(X, W_encode1), b_encode1))

W_encode2 = tf.Variable(tf.random_uniform([n_hidden1, n_hidden2], -1., 1.))
b_encode2 = tf.Variable(tf.random_uniform([n_hidden2], -1., 1.))

encoder_h2 = tf.nn.sigmoid(tf.add(tf.matmul(encoder_h1, W_encode2), b_encode2))

W_decode1 = tf.Variable(tf.random_uniform([n_hidden2, n_hidden1], -1., 1.))
b_decode1 = tf.Variable(tf.random_uniform([n_hidden1], -1., 1.))

decoder = tf.nn.sigmoid(tf.add(tf.matmul(encoder_h2, W_decode1), b_decode1))

W_decode2 = tf.Variable(tf.random_uniform([n_hidden1, n_input], -1., 1.))
b_decode2 = tf.Variable(tf.random_uniform([n_input], -1., 1.))

output = tf.nn.sigmoid(tf.add(tf.matmul(decoder, W_decode2), b_decode2))

cost = tf.reduce_mean(tf.square(X - output))
optimizer = tf.train.AdamOptimizer(learning_rate).minimize(cost)

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    total_batch = int(mnist.train.num_examples / batch_size)

    for epoch in range(epoch_num):
        avg_cost = 0
        for i in range(total_batch):
            batch_xs, batch_ys = mnist.train.next_batch(batch_size)
            # create random noise
            batch_xs_noisy = batch_xs + np.random.normal(loc=0.0, scale=1.0, size=batch_xs.shape)
            _, cost_val = sess.run([optimizer, cost], feed_dict={X: batch_xs_noisy})
            avg_cost += cost_val / total_batch
        print('Epoch:', '%d' % (epoch + 1), 'cost:', '{:.9f}'.format(avg_cost))

    batch_xs, _ = mnist.train.next_batch(batch_size)
    batch_xs_noisy = batch_xs + np.random.normal(loc=0.0, scale=1.0, size=batch_xs.shape)
    samples = sess.run(output, feed_dict={X: batch_xs_noisy})
    fig, ax = plt.subplots(3, 10, figsize=(10, 2))

    for i in range(10):
        ax[0][i].set_axis_off()
        ax[1][i].set_axis_off()
        ax[2][i].set_axis_off()
        ax[0][i].imshow(np.reshape(batch_xs[i], (28, 28)))
        ax[1][i].imshow(np.reshape(batch_xs_noisy[i], (28, 28)))
        ax[2][i].imshow(np.reshape(samples[i], (28, 28)))
    plt.show()