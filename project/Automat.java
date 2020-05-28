package Automatisation;

import static org.junit.Assert.fail;
import static org.junit.jupiter.api.Assertions.assertEquals;

import java.io.File;
import java.io.FileInputStream;
import java.util.Arrays;
import java.util.Collections;
import java.util.NoSuchElementException;
import java.util.concurrent.TimeUnit;

import javax.swing.JFrame;

import org.jopendocument.dom.OOUtils;
import org.jopendocument.dom.spreadsheet.Sheet;
//import org.apache.poi.sl.usermodel.Sheet;
import org.jopendocument.dom.spreadsheet.SpreadSheet;
import org.jopendocument.model.OpenDocument;
import org.jopendocument.panel.ODSViewerPanel;
import org.jopendocument.print.DefaultDocumentPrinter;
import org.jopendocument.util.FileUtils;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.internal.TextListener;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.openqa.selenium.Alert;
import org.openqa.selenium.By;
import org.openqa.selenium.By.ByClassName;
import org.openqa.selenium.Dimension;
import org.openqa.selenium.NoAlertPresentException;
import org.openqa.selenium.OutputType;
import org.openqa.selenium.TakesScreenshot;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.chrome.ChromeOptions;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.Wait;
import org.openqa.selenium.support.ui.WebDriverWait;
import org.openqa.selenium.JavascriptExecutor;
import org.openqa.selenium.Keys;




public class Automat {
  private WebDriver driver;
  //private String baseUrl;
  private boolean acceptNextAlert = true;
  private StringBuffer verificationErrors = new StringBuffer();
  static String _latitude;
  static String _longitude;
  static String _distance;

  
  public static void main(String args[]) {
	  _latitude = args[0];
	  _longitude = args[1];
	  _distance = args[2];
	  JUnitCore junit = new JUnitCore();
	  junit.addListener(new TextListener(System.out));
	  Result result = junit.run(Automat.class); 
	  if (result.getFailureCount() > 0) {
	    System.out.println("Test failed.");
	    System.exit(1);
	  } else {
	    System.out.println("Test finished successfully.");
	    System.exit(0);
	  }
  }
  
  public static String MakeUrl(String latitude, String longitude, String zoom)
  {
	  String ret = "";
	  ret = "https://www.google.fr/maps/@" + latitude + "," + longitude + "," + zoom + "m" + "/data=!3m1!1e3";
	  //ret = "https://www.google.com/maps/@" + latitude + "," + longitude + "," + zoom + "z";
	  System.out.println(ret);
	  return ret;
  }

  @Before
  public void setUp() throws Exception {
	System.setProperty("webdriver.chrome.driver", "chromedriver.exe" );//"D:/dev/selenium/chromedriver.exe");//
	
	ChromeOptions options = new ChromeOptions();
	//options.addArguments("-incognito");
	options.addArguments("start-maximized");
	//options.addArguments("disable-infobars");
	//options.addArguments("--disable-popup-blocking");
	
	options.setExperimentalOption("excludeSwitches", Collections.singletonList("enable-automation"));
	options.setExperimentalOption("useAutomationExtension", false);
	

    driver = new ChromeDriver(options);
    
    //baseUrl = "https://www.google.com/";
    driver.manage().timeouts().implicitlyWait(4, TimeUnit.SECONDS);
    //driver.manage().window().setSize(new Dimension(1280,720));
    driver.manage().window().maximize();
    
    String url = MakeUrl(_latitude,_longitude,_distance);//String url = MakeUrl("46.83","5.73","809882");
	driver.get(url);
  }
  
  
  


  @Test
  public void testLoginValideEtMdpValide() throws Exception {

	  //String url = MakeUrl(_latitude,_longitude,_distance);
	  System.out.println("Start");
	
    WebDriverWait wait = new WebDriverWait(driver, 1);
    
    try
    {
    	wait.until(ExpectedConditions.visibilityOfElementLocated(By.className("toto")));
    } catch (Exception e)
    {
    	System.out.println("waited 1 sec");
    }
    
    //driver.manage().window().fullscreen();
    

    wait.until(ExpectedConditions.visibilityOfElementLocated(By.className("section-homescreen-expand-entrypoint-icon"))); //class="noprint maps-sprite-common-chevron-left"
    
    WebElement dir = driver.findElement(By.className("section-homescreen-expand-entrypoint-icon"));
    
    
    
    dir.click();
    
    //consent-bump
    String jss = "var element = document.getElementById(\"consent-bump\");element.remove();";
    ((JavascriptExecutor)driver).executeScript(jss);
    
//    try
//    {
//    	wait.until(ExpectedConditions.visibilityOfElementLocated(By.className("toto")));
//    } catch (Exception e)
//    {
//    	System.out.println("waited 1 sec");
//    }
    
//    try
//    {
//    	 WebElement closeRead = driver.findElement(By.xpath("//a[contains(text(),'Me le rappeler plus tard')]"));//("widget-consent-button-later ripple-container")
//    	 closeRead.click();
//    } catch (Exception e)
//    {
//    	System.out.println("nothing to click");
//    }
    
    wait.until(ExpectedConditions.visibilityOfElementLocated(By.xpath("//div[@id='pane']/div/div[3]/button")));
    // //div[@id='pane']/div/div[3]/button
    WebElement panelReduce = driver.findElement(By.xpath("//div[@id='pane']/div/div[3]/button"));
    
    panelReduce.click();
    
    
    
    try
    {
    	wait.until(ExpectedConditions.visibilityOfElementLocated(By.className("toto")));
    }
    catch (Exception e)
    {
    	System.out.println("waited 1 sec");
    }
    
    String zoom = GetZoom(driver.getCurrentUrl());
    
    File scrFile = ((TakesScreenshot)driver).getScreenshotAs(OutputType.FILE);
    
    // Now you can do whatever you need to do with it, for example copy somewhere
    //FileUtils.copyFile(scrFile, new File(_longitude + "_" + _latitude + "_" + _distance + ".png"));
    
    FileUtils.copyFile(scrFile, new File(zoom+".png"));
    
  }
  
  public String GetZoom(String url)
  {
	  String[] split = url.split(",");
	  String[] split2 = split[2].split("m");
	  return split2[0];
  }

  @After
  public void tearDown() throws Exception {
    driver.quit();
    String verificationErrorString = verificationErrors.toString();
    if (!"".equals(verificationErrorString)) {
      fail(verificationErrorString);
    }
  }

  private boolean isElementPresent(By by) {
    try {
      driver.findElement(by);
      return true;
    } catch (NoSuchElementException e) {
      return false;
    }
  }

  private boolean isAlertPresent() {
    try {
      driver.switchTo().alert();
      return true;
    } catch (NoAlertPresentException e) {
      return false;
    }
  }

  private String closeAlertAndGetItsText() {
    try {
      Alert alert = driver.switchTo().alert();
      String alertText = alert.getText();
      if (acceptNextAlert) {
        alert.accept();
      } else {
        alert.dismiss();
      }
      return alertText;
    } finally {
      acceptNextAlert = true;
    }
  }
}
