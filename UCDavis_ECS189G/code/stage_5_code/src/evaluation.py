'''
Concrete Evaluate class for a specific evaluation metrics
'''

# Copyright (c) 2022-Current Jialiang Wang <jilwang804@gmail.com>
# Copyright (c) 2017-Current Jiawei Zhang <jiawei@ifmlab.org>
# License: TBD

from .base.evaluate import evaluate
from sklearn.metrics import accuracy_score


class Evaluate_Accuracy(evaluate):
    data = None
    
    def evaluate(self):
        print('Evaluating performance...')
        return accuracy_score(self.data['true_y'], self.data['pred_y'])


def evaluate_accuracy(y_pred, y_true):
    print('Evaluating performance...')
    prediction = y_pred.max(1)[1].type_as(y_pred)
    correct = prediction.eq(y_true).double()
    correct = correct.sum()

    return correct / len(y_true)

