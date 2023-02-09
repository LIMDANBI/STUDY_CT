import java.io.*;

public class Main {
	
	static StringBuilder sb = new StringBuilder();
	
	static int N;
	static int SingleDigitPrime[] = {2, 3, 5, 7};
	
	public static void main(String[] args) throws Exception {
		// System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = br.read()-'0';
		
		for(int start : SingleDigitPrime) solution(start, 1);
		System.out.println(sb.toString());
	}

	static void solution(int num, int cnt) {
		if(!isPrime(num)) return; // 소수가 아닌 경우 
		if(cnt == N) {
			sb.append(num).append("\n"); // N자리 신기한 소수
			return ;
		}
		for(int i=1; i<10; i+=2) { // 짝수로 끝나면 소수가 될 수 없음 
			solution(Integer.parseInt(num+""+i) , cnt+1);
		}
	}

	static boolean isPrime(int num) {
		for(int i=2; i*i<=num; i++) {		
			if(num%i == 0) return false;
		} return true;
	}
}