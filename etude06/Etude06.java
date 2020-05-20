import java.awt.*;
import javax.swing.*;
import java.util.Scanner;
import java.util.Vector;
import java.lang.Math;

public class Etude06 {
	public static final int WINDOW_WIDTH = 1000;
	public static final int WINDOW_HEIGHT = 700;
	
	public static class Quilt extends JFrame {
		Vector<Layer> layers = new Vector<Layer>();
		
		// to be filled with origin locations to print each square
		// the contents of the i'th vector correspond to squares to be printed in the i'th layer
		Vector<Vector<Point>> origins = new Vector<Vector<Point>>();
		
		int std_dim = -1; // the length of one side of a square with scale 1.0
		int std_halfside = -1; // the length of half of one side of a square with scale 1.0
		
		public Quilt(Vector<Layer> layers) {
			this.layers = layers;
			
			// initialize origins
			for (int i = 0; i < layers.size(); i++) {
				Vector<Point> vec = new Vector<Point>();
				origins.add(vec);
			}
			
			setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	        setLocationRelativeTo(null);
	        setVisible(true);
		}
		
		public void recurse(Point center, int level) {
			// base case
			if (level >= layers.size()) {
				return;
			}
						
			// get scale
			double scale = layers.get(level).scale;
			int halfside = (int) (scale * std_halfside);
						
			// create 4 corners based on center, scale of the layer, and the standard dimension
			Point top_left, top_right, bottom_left, bottom_right;
			top_left = new Point(center.x - halfside, center.y - halfside);
			top_right = new Point(center.x + halfside, center.y - halfside);
			bottom_left = new Point(center.x - halfside, center.y + halfside);
			bottom_right = new Point(center.x + halfside, center.y + halfside);
			
			
			
			// add origin point to list
			origins.get(level).add(top_left); 
			
			
			// increment level, indicating layer number
			level++;
			
			// recurse
			recurse(top_left, level);
			recurse(top_right, level);
			recurse(bottom_left, level);
			recurse(bottom_right, level);
		}
		
		public void paint(Graphics g){
			// calculate sum of scales
	        double sum_of_scales = 0;
	        for (Layer layer : layers) {
	        	sum_of_scales += layer.scale;
	        }
	        
	        // calculate the dimensions of a square with scale 1.0
	        std_dim = (int) ((double)Math.min(WINDOW_HEIGHT, WINDOW_WIDTH) * 0.85 / sum_of_scales);
	        std_halfside = std_dim / 2;
	        
	        // determine the center of the first square
			Point center_frame = new Point(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	        
	        // recurse
	        recurse(center_frame, 0);
	        
	        // origins vector is now filled.  Print.
	        for (int i = 0; i < origins.size(); i++) {
	        	Layer layer = layers.get(i);
	        	double scale = layer.scale;
	        	Color color = new Color(layer.r, layer.g, layer.b);
	        	g.setColor(color);
	        	Vector<Point> points = origins.get(i);
	        	for (int j = 0; j < origins.get(i).size(); j++) {
	        		Point point = points.get(j);
	        		int sidelength = (int) (scale * std_halfside * 2);
	        		g.fillRect(point.x, point.y, sidelength, sidelength);
	        	}
	        }
	    }
	}
	
	public static class Layer {
		public double scale;
		public int r, g, b;
		
		public Layer(double scale, int r, int g, int b) {
			this.scale = scale;
			this.r = r;
			this.g = g;
			this.b = b;
		}
	}
	
	public static void main (String[] args) {
		
		
		Vector<Layer> layers = new Vector<Layer>();
		
		// get input 
		Scanner scan = new Scanner(System.in);
		String line = "";
		while (scan.hasNextLine()) {
			line = scan.nextLine();
			String[] params = line.split(" ");
			double scale = Double.parseDouble(params[0]);
			int r = Integer.parseInt(params[1]);
			int g = Integer.parseInt(params[2]);
			int b = Integer.parseInt(params[3]);
			
			Layer layer = new Layer(scale, r, g, b);
			layers.add(layer);
		}
		
		// create quilt from layers
		new Quilt(layers);
	}

}
