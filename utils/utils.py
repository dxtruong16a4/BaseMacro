import pygetwindow
import requests
import os
import cv2
import pytesseract
import numpy as np
import winreg as reg
from PIL import Image
from typing import Union, Tuple
from src.config import img_dir

def check_connection():
    try:
        requests.get("https://www.google.com")
        return True
    except requests.exceptions.RequestException:
        return False
    
def getDefaultBrowser():
    """
    Get the default browser of the user and map it to a window title.
    """
    path = r"Software\Microsoft\Windows\Shell\Associations\UrlAssociations\http\UserChoice"
    browser = None
    try:
        with reg.OpenKey(reg.HKEY_CURRENT_USER, path) as key:
            progid = reg.QueryValueEx(key, 'Progid')[0]
            browser_titles = {
                "ChromeHTML": "Chrome",
                "FirefoxHTML": "Firefox",
                "MSEdgeHTM": "Edge",
                "OperaGXHTML": "Opere"
            }
            browser = browser_titles.get(progid, None)
    except FileNotFoundError:
        pass
    return browser

def maximizeWindowTitle(title):
    """
    Maximize the window with the given title.

    Parameters:
    title (str): The title of the window to open.
    """
    try:
        windows = pygetwindow.getWindowsWithTitle(title)
        if windows:
            windows[0].maximize()
    except IndexError:
        pass

def get_image_position(img1, img2, threshold=0.8):
    """
    Get the position and size of img1 within img2 using template matching.

    Parameters:
    img1 (PIL.Image.Image): The smaller image to search for within img2.
    img2 (PIL.Image.Image): The larger image in which to search for img1.
    threshold (float): The similarity threshold (between 0 and 1) to consider a match. 
                       Default is 0.8, meaning a match is found if the similarity score 
                       is 0.8 or higher.

    Returns:
    tuple: (x, y, width, height) of the matched region if the similarity score 
           is greater than or equal to the threshold, otherwise (None, None, None, None).
    """
    img1_gray = img1.convert('L')
    img2_gray = img2.convert('L')
    img1_np = np.array(img1_gray)
    img2_np = np.array(img2_gray)
    result = cv2.matchTemplate(img2_np, img1_np, cv2.TM_CCOEFF_NORMED)
    _, max_val, _, max_loc = cv2.minMaxLoc(result)

    if max_val >= threshold:
        x, y = max_loc
        width, height = img1.size
        return x, y, width, height
    else:
        return None, None, None, None

def capture(img_name, region=None):
    import pyautogui
    """
    Capture a screenshot (entire screen or specific region) and save it with the specified name.

    Parameters:
    img_name (str): The name to use for the saved image file.
    region (Tuple[int, int, int, int], optional): The region to capture (x, y, width, height). Defaults to None for full screen.
    """
    if region:
        x, y, width, height = region
        screenshot = pyautogui.screenshot(region=(x, y, width, height))
    else:
        screenshot = pyautogui.screenshot()

    screenshot_cv = cv2.cvtColor(np.array(screenshot), cv2.COLOR_RGB2BGR)
    img_dir.mkdir(parents=True, exist_ok=True)
    filename = img_dir / f'{img_name}.jpg'
    cv2.imwrite(str(filename), screenshot_cv)

def check_img_similarity(
        img1: Union[str, np.ndarray],
        img2: Union[str, np.ndarray],
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
    elif isinstance(img1, np.ndarray) and isinstance(img2, np.ndarray):
        img_a_gray = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY) if len(img1.shape) == 3 else img1
        img_b_gray = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY) if len(img2.shape) == 3 else img2
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

def getTextFromImage(img_path):
    """
    Get text from an image using OCR.

    Parameters:
    img_path (str): The path to the image file.

    Returns:
    str: The text extracted from the image.
    """
    try:
        pytesseract.pytesseract.tesseract_cmd = r"C:\Program Files\Tesseract-OCR\tesseract.exe"        
        if not os.path.exists(img_path):
            return "Error: Image file not found."
        img = Image.open(img_path)
        text = pytesseract.image_to_string(img, lang="eng")
        return text.strip()
    except Exception as e:
        return f"Error: {e}"