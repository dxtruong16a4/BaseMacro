from pathlib import Path
from PIL import Image
from typing import Union, Tuple
import requests
import pyautogui
import cv2
import numpy as np

dir = Path(__file__).resolve().parent.parent
img_dir = dir / 'img'

def check_connection():
    try:
        requests.get("https://www.google.com")
        return True
    except requests.exceptions.ConnectionError:
        return False

def capture(img_name):
    """
    Capture a screenshot and save it with the specified name.

    Parameters:
    img_name (str): The name to use for the saved image file.
    """
    screenshot = pyautogui.screenshot()
    screenshot_cv = cv2.cvtColor(np.array(screenshot), cv2.COLOR_RGB2BGR)
    output_folder = Path('img')
    output_folder.mkdir(parents=True, exist_ok=True)
    filename = output_folder / f'{img_name}.jpg'
    cv2.imwrite(str(filename), screenshot_cv)
    # print(f"Đã lưu ảnh vào: {filename}")

def check_img_similarity(
        img1: Union[str, Image.Image],
        img2: Union[str, Image.Image],
        search_region: Tuple[int, int, int, int] = None,
        threshold: float = 0.8
    ) -> bool:
    """
    Check the similarity between two images or within a specified search region.

    Parameters:
    img1 (Union[str, PIL.Image.Image]): The filename of the first image (without extension) or a PIL Image object.
    img2 (Union[str, PIL.Image.Image]): The filename of the second image (without extension) or a PIL Image object.
    search_region (Tuple[int, int, int, int], optional): The region (x, y, width, height) to search in the second image. Default is None.
    threshold (float): The similarity threshold (between 0 and 1) to consider a match. Default is 0.8.

    Returns:
    bool: True if the images are similar within the search region or overall, False otherwise.
    """
    if isinstance(img1, str) and isinstance(img2, str):
        image_a_path = img_dir / f'{img1}.jpg'
        image_b_path = img_dir / f'{img2}.jpg'
        img_a_gray = cv2.imread(str(image_a_path), cv2.IMREAD_GRAYSCALE)
        img_b_gray = cv2.imread(str(image_b_path), cv2.IMREAD_GRAYSCALE)
        if img_a_gray is None or img_b_gray is None:
            raise FileNotFoundError("One or both images could not be loaded.")
    elif isinstance(img1, Image.Image) and isinstance(img2, Image.Image):
        img_a_gray = np.array(img1.convert('L'))
        img_b_gray = np.array(img2.convert('L'))
    else:
        raise ValueError("img1 and img2 must both be either filenames or PIL Image objects.")
    if search_region:
        x, y, search_width, search_height = search_region
        search_area = img_b_gray[y:y + search_height, x:x + search_width]
    else:
        search_area = img_b_gray
    result = cv2.matchTemplate(search_area, img_a_gray, cv2.TM_CCOEFF_NORMED)
    _, max_val, _, _ = cv2.minMaxLoc(result)
    return max_val >= threshold

def get_image_position(img1, img2, threshold=0.8):
    """
    Get the position of img1 within img2 using template matching.

    Parameters:
    img1 (PIL.Image.Image): The smaller image to search for within img2.
    img2 (PIL.Image.Image): The larger image in which to search for img1.
    threshold (float): The similarity threshold (between 0 and 1) to consider a match. 
                       Default is 0.8, meaning a match is found if the similarity score 
                       is 0.8 or higher.

    Returns:
    tuple: (x, y) coordinates of the top-left position of the matched region if the similarity score 
           is greater than or equal to the threshold, otherwise (None, None).
    """
    img1_gray = img1.convert('L')
    img2_gray = img2.convert('L')
    img1_np = np.array(img1_gray)
    img2_np = np.array(img2_gray)
    result = cv2.matchTemplate(img2_np, img1_np, cv2.TM_CCOEFF_NORMED)
    _, max_val, _, max_loc = cv2.minMaxLoc(result)
    if max_val >= threshold:
        return max_loc
    else:
        return None, None
