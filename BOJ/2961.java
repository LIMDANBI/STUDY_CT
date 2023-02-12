import java.io.*;
import java.util.*;

public class Main {
	
	static class Ingredient{
		int S, B;

		public Ingredient(int s, int b) {
			S = s;
			B = b;
		}
	}
	
	static int N, ans = Integer.MAX_VALUE;
	static Ingredient[] ingredients;
	
	public static void main(String[] args) throws Exception {
		//System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		
		N = Integer.parseInt(st.nextToken()); //재료의 개수 
		ingredients = new Ingredient[N];
		
		int s, b;
		for(int i=0; i<N; i++) {
			st = new StringTokenizer(br.readLine()); 
			s = Integer.parseInt(st.nextToken()); // 사용한 재료의 신맛의 곱
			b = Integer.parseInt(st.nextToken()); // 쓴맛은 합
			ingredients[i] = new Ingredient(s, b);
		}
		
		solution(0, 1, 0);
		System.out.println(ans); // 신맛과 쓴맛의 차이가 가장 작은 요리의 차이
	}

	static void solution(int cnt, int sour, int bitter) {
		if(cnt == N) {
			if(sour==1) return;
			ans = Math.min(ans, Math.abs(sour-bitter));
			return;
		}
		
		solution(cnt+1, sour*ingredients[cnt].S, bitter+ingredients[cnt].B);
		solution(cnt+1, sour, bitter);
	}
}