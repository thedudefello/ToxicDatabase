package main;

import java.io.BufferedReader;
import java.io.InputStreamReader;

import java.net.URL;
import java.net.URLConnection;



public class Scraper {

	public Scraper() {

	}
	
	public int getPewdiepieCount() {
		try {
			return this.parseJson(this.getJson("https://www.googleapis.com/youtube/v3/channels?part=statistics&id=UC-lHJZR3Gqxm24_Vd_AJ5Yw&fields=items/statistics/subscriberCount&key=AIzaSyACZdXbrIijp3kLgAGNIdSCe7uxxIvo9wY"));
		} catch (Exception e) {
			e.printStackTrace();
			return 0;
		}
	}

	public int getTSeriesCount() {
		try {
			return this.parseJson(this.getJson("https://www.googleapis.com/youtube/v3/channels?part=statistics&id=UCq-Fj5jknLsUf-MWSy4_brA&fields=items/statistics/subscriberCount&key=AIzaSyACZdXbrIijp3kLgAGNIdSCe7uxxIvo9wY"));
		} catch (Exception e) {
			e.printStackTrace();
			return 0;
		}
	}

	public  int parseJson(String json) {
		// crude but light weight way of parsing target values
		String tail = json.split(":")[3];
		return Integer.parseInt(tail.split("\"")[1]);
		
	}
	public String getJson(String targetUrl) throws Exception {
		URL target = new URL(targetUrl);
        URLConnection targetc = target.openConnection();
        BufferedReader in = new BufferedReader(
                                new InputStreamReader(
                                		targetc.getInputStream()));
        String inputLine;
        String res = "";

        while ((inputLine = in.readLine()) != null) {
        	res += inputLine;
        } 
        in.close();
		return res;
	}
	
}
