import glob
from os import getcwd
from os.path import join

from anshitsu.process.processor import Processor

from PIL import Image


def grayscaling(path: str):
    """
    grayscaling 画像をグレースケール化する

    Args:
        path (str): ファイルパス

    Returns:
        Image: 与えられたパスの画像をグレースケール化したもの
    """
    image = Image.open(path)
    retouch = Processor(image, grayscale=True)
    gray_image = retouch.process()
    return gray_image


def bundle_grayscaling(dir: str):
    """
    bundle_grayscaling 指定されたディレクトリ内のGIF、PNG、JPEGファイルをグレースケール化する

    Args:
        dir (str): 画像を格納したディレクトリ
    """
    path_list: list[str] = []
    for ext in ('*.gif', '*.png', '*.jpg', '*.jpeg'):
        path_list.extend(glob.glob(join(dir, ext)))

    for i in path_list:
        try:
            img = grayscaling(i)
            img.save(i)
        except IndexError:
            print("以下のファイルを処理するときにエラーが発生しました。")
            print(i)
        finally:
            print("ファイル処理が完了しました。")
            print(i)
    return


image_path = getcwd() + "/images"
print(image_path)
bundle_grayscaling(image_path)
