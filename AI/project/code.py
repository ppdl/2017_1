import pickle
import pandas as pd
import numpy as np
import gensim
from fuzzywuzzy import fuzz
from nltk.corpus import stopwords
from tqdm import tqdm
from scipy.stats import skew, kurtosis
from scipy.spatial.distance import cosine, cityblock, jaccard, canberra, euclidean, minkowski, braycurtis
from nltk import word_tokenize
stop_words = stopwords.words('english')
import datetime

'''
def wmd(s1, s2):
    s1 = str(s1).lower().split()
    s2 = str(s2).lower().split()
    stop_words = stopwords.words('english')
    s1 = [w for w in s1 if w not in stop_words]
    s2 = [w for w in s2 if w not in stop_words]
    return model.wmdistance(s1, s2)


def norm_wmd(s1, s2):
    s1 = str(s1).lower().split()
    s2 = str(s2).lower().split()
    stop_words = stopwords.words('english')
    s1 = [w for w in s1 if w not in stop_words]
    s2 = [w for w in s2 if w not in stop_words]
    return norm_model.wmdistance(s1, s2)


def sent2vec(s):
    words = str(s).lower().decode('utf-8')
    words = word_tokenize(words)
    words = [w for w in words if not w in stop_words]
    words = [w for w in words if w.isalpha()]
    M = []
    for w in words:
        try:
            M.append(model[w])
        except:
            continue
    M = np.array(M)
    v = M.sum(axis=0)
    return v / np.sqrt((v ** 2).sum())


data = pd.read_csv('data/test.csv', encoding = 'ISO-8859-1')

model = gensim.models.KeyedVectors.load_word2vec_format('data/GoogleNews-vectors-negative300.bin.gz', binary=True)
data['wmd'] = data.apply(lambda x: wmd(x['question1'], x['question2']), axis=1)


norm_model = gensim.models.KeyedVectors.load_word2vec_format('data/GoogleNews-vectors-negative300.bin.gz', binary=True)
data['norm_wmd'] = data.apply(lambda x: norm_wmd(x['question1'], x['question2']), axis=1)

question1_vectors = np.zeros((data.shape[0], 300))
error_count = 0

for i, q in tqdm(enumerate(data.question1.values)):
    question1_vectors[i, :] = sent2vec(q)

question2_vectors  = np.zeros((data.shape[0], 300))
for i, q in tqdm(enumerate(data.question2.values)):
    question2_vectors[i, :] = sent2vec(q)

data['cosine_distance'] = [cosine(x, y) for (x, y) in zip(np.nan_to_num(question1_vectors),
                                                          np.nan_to_num(question2_vectors))]


data.to_csv('data/test_features.csv', index=False)
'''
#Extract Features
#--------------------------------------------------------------
#Learning



#--------------------------------------------------------------
#Calculating
data = pd.read_csv('data/test_features.csv', encoding = 'ISO-8859-1')
print("Prorcessing...")

cosDistance_ColumnPosition = 5

result = np.zeros((data.shape[0],2), dtype='int32')
for i in range(data.shape[0]):
	if(i%10000 == 0): print("[",datetime.datetime.now().strftime('%H:%M:%S'),"]",i,"/",data.shape[0],"completed")
	result[i,0] = i
	if(abs(data.iloc[i,cosDistance_ColumnPosition]) < 0.25):
		result[i,1] = 1
	elif(abs(data.iloc[i,cosDistance_ColumnPosition]) >= 0.25):
	    result[i,1] = 0

df = pd.DataFrame(data = result[0:, 0:], columns=['test_id', 'is_duplicate'])


df.to_csv('data/result.csv', index=False)
