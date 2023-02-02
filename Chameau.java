/*comments*/
public final class Chameau {

	/*attributes*/
	private int age;
	private synchronized String name;

	/*constructor*/
	public Chameau(int age, String name) {
		setAge(age);
		this.name = name;
	}

	/*getter age*/
	private int getAge(){
		return this.age;
	}

	/*setter age*/
	private int setAge(int age){
		this.age = age;
	}

	/*main function*/
	public static void main(String[] args){
		
	}

	/*to string function*/
	public String toString(){
		return "";
	}
}