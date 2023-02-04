/*comments*/
public class Tableau {

	/*attributes*/
	public int age;
	public String name;

	/*constructor*/
	public Tableau(int age, String name) {
		setAge(age);
		setName(name);
	}

	/*getter age*/
	public int getAge(){
		return this.age;
	}
	/*getter name*/
	public String getName(){
		return this.name;
	}

	/*setter age*/
	public int setAge(int age){
		this.age = age;
	}
	/*setter name*/
	public String setName(String name){
		this.name = name;
	}

	/*to string function*/
	public String toString(){
		return "";
	}

	/*equals function*/
	public boolean equals(Tableau other) {
		/*pointers*/
		if (this == other) {
			return true;
		}
		if (other == null) {
			return false;
		}
		/*age*/
		if (this.age != other.age) {
			return false;
		}
		/*name*/
		if (this.name == null) {
			if (other.name != null) {
				return false;
			}
		} else if (!this.name.equals(other.name)) {
			return false;
		}
		/*it's true :)*/
		return true;
	}

	/*main function*/
	public static void main(String[] args){
		
	}

}