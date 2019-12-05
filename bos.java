import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashSet;
import java.util.Scanner;

public class bos {

	HashSet<String> tempBag = new HashSet<>();

	public static void list(File file) {
		
		String line = null;
		
		try {
			
			FileReader fileReader = new FileReader(file.getName());
			BufferedReader bufferedReader = new BufferedReader(fileReader);
			
			while((line = bufferedReader.readLine()) != null) {
                System.out.println(line);
            }
			
			bufferedReader.close();
		}
		catch(IOException ex){
			
			 System.out.println("Unable to open file '" + file.getName() + "'"); 
			 
		}
	}
	
	public static void add(File file, String content) {
		
		try {
			
			if(contains(file, content)) {
				throw new IOException("That string already exists!");
			}
			
			BufferedWriter writer = new BufferedWriter(new FileWriter(file.getName(), true));
			
			writer.newLine();
			writer.write(content);
			writer.close();
			
		}
		catch(IOException ex) {
			
			System.out.println(ex);
			
		}
	}
	
	public static void delete(File file, String content) {
		
		String line = null;
		String lineTwo = null;
		File tempFile = new File("./output.txt");
		
		try {
			
			FileReader fileReader = new FileReader(file.getName());
			BufferedReader bufferedReader = new BufferedReader(fileReader);
			
			BufferedWriter writer = new BufferedWriter(new FileWriter(tempFile.getName(), true));
			
			while((line = bufferedReader.readLine()) != null) {
				
                if(!line.equals(content)) {
                	
        			writer.write(line);
        			writer.newLine();
        			
                	
                }
            }
			
			PrintWriter pw = new PrintWriter(file.getName());
			pw.close();
			
			bufferedReader.close();
			writer.close();
			
			BufferedReader tempReader = new BufferedReader(new FileReader(tempFile.getName()));
			BufferedWriter outputWriter = new BufferedWriter(new FileWriter(file.getName(), true));
			
			while((lineTwo = tempReader.readLine()) != null) {
                	
    			outputWriter.write(lineTwo);
    			outputWriter.newLine();
                	
            }
			
			outputWriter.close();
			tempReader.close();
			
			tempFile.delete();
			
			
		}
		catch(IOException ex) {
			
			System.out.println("Unable to open file '" + file.getName() + "'"); 
			
		}
	}
	
	public static boolean contains(File file, String content) {
		
		String line = null;
		
		try {
			
			FileReader fileReader = new FileReader(file.getName());
			BufferedReader bufferedReader = new BufferedReader(fileReader);
			
			while((line = bufferedReader.readLine()) != null) {
                
				if(content.equals(line)) {
					return true;
				}
				
            }
			
			bufferedReader.close();
			
			return false;
			
		}
		catch(IOException ex){
			
			 System.out.println("Unable to open file '" + file.getName() + "'");
			 return false;
			 
		}
	}
	
	
	public static void main(String[] args) {
		
		String fileName = args[0];
		
		File file = new File("./"+fileName);
		
		try {
			
			if(file.createNewFile()) {
				
				System.out.println("file created");
				Scanner scan = new Scanner(System.in);
				
				while(true) {
					String command = scan.nextLine();
					String mainCommand = command.substring(0, 1);
					
					if(mainCommand.equals("l")) {
						
						list(file);
						
					}else if(mainCommand.equals("a")) {
						
						add(file, command.substring(2, command.length()));

					}else if(mainCommand.equals("d")) {
						
						delete(file, command.substring(2, command.length()));
						
					}
				}
				
				
				
			}else {
				
				System.out.println("already exists");
				Scanner scan = new Scanner(System.in);
				
				while(true) {
					String command = scan.nextLine();
					String mainCommand = command.substring(0, 1);
					
					if(mainCommand.equals("l")) {
						
						list(file);
						
					}else if(mainCommand.equals("a")) {
						
						add(file, command.substring(2, command.length()));
						
					}else if(mainCommand.equals("d")) {
						
						delete(file, command.substring(2, command.length()));
						
					}
				}
				
			}
			
			
		} catch (IOException e) {
			System.out.println("error");
			e.printStackTrace();
		}
		
	}
	
}
