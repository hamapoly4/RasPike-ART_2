from multiprocessing import shared_memory
import numpy as np

# データを準備
data = np.array([1, 2, 3, 4], dtype=np.int32)

# 共有メモリ作成
shm = shared_memory.SharedMemory(name="yuta", create=True, size=data.nbytes)

# 共有メモリにデータを書き込み
buffer = np.ndarray(data.shape, dtype=data.dtype, buffer=shm.buf)
buffer[:] = data[:]  # データコピー

# 共有メモリの名前を出力
print(f"Shared memory name: {shm.name}")

input("Press Enter to release shared memory...")
shm.close()
shm.unlink()    #memorikaihou
