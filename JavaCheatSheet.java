import java.util.*;
import java.io.*;
import java.math.*;
public class JavaCheetSheet {
	public static void main(String[] args)throws Exception {
		Integer[] v = {1, 5, 2, 4, 3};
		Arrays.sort(v, new Comp());

		LinkedList<Integer> linkedlist = new LinkedList<Integer>();
		linkedlist.addLast(1); linkedlist.addFirst(2); linkedlist.addFirst(3);
		System.out.println(linkedlist.peekFirst());
		linkedlist.removeLast();

		ArrayList<Integer> list = new ArrayList<Integer>();
		list.add(1); list.add(2); list.add(3); list.add(5);
		list.remove(list.size() - 1); list.remove((Integer)1);
		for (int i = 0; i < list.size(); i++)
			System.out.print(list.get(i));
		Collections.sort(list, new Comp());
		for (int i : list)
			System.out.print(i);

		Set<String> set = new TreeSet<String>(); // or HashSet
		set.add("abc"); set.add("ghi"); set.add("def");
		for (String s : set)
			System.out.println(s);
		System.out.println(set.contains("abc"));
		set.clear();

		Map<String, String> map = new TreeMap<String, String>(); // or HashMap
		map.put("k1", "v1"); map.put("k2", "v2");
		System.out.println(map.containsKey("k1"));
		System.out.println(map.get("k2"));
		for (Map.Entry<String, String> entry : map.entrySet()) {
			System.out.println(entry.getKey() + " " + entry.getValue());
		}

		BigInteger i1 = new BigInteger("1234567");
		BigInteger i2 = BigInteger.valueOf(23456);
		System.out.println(i1.add(i2));
		System.out.println(i1.isProbablePrime(32));
		System.out.println(i1.modInverse(i2));

		StringBuilder sb = new StringBuilder();
		sb.append("abc"); sb.append(123);
		System.out.println(sb.toString());
	}
}
class Comp implements Comparator<Integer> {
	public int compare(Integer lhs, Integer rhs) {
		return rhs - lhs;
	}
}
class Scan {
	BufferedReader buffer;
	StringTokenizer tok;
	Scan() {
		buffer = new BufferedReader(new InputStreamReader(System.in));
	}
	boolean hasNext() {
		while (tok == null || !tok.hasMoreElements()) {
			try {
				tok = new StringTokenizer(buffer.readLine());
			} catch (Exception e) {
				return false;
			}
		}
		return true;
	}
	String next() {
		if (hasNext()) return tok.nextToken();
		return null;
	}
	String nextLine() {
		if (hasNext()) return tok.nextToken("\n");
		return null;
	}
	int nextInt() {
		return Integer.parseInt(next());
	}
}
