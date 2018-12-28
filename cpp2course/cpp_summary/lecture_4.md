---


---

<p><strong>std::bind</strong><br>
bind - sth can be called</p>
<pre><code>bind(f, 1, 2, 3)() //f(1,2,3)
bind(f, 4, _1, 5) (6) //f(4,5,6)
bind(f, _3,_2, _1)(7,8,9) //f(9,8,7)
bind(f,_2,_2,_3)(10,11,12) //f(11,11,12)
bind(f,_1, bind(g,_2,42) 43) (44,45) //f(44,g(45,42),43)
</code></pre>
<p><strong>std::placeholder&lt;N&gt;</strong><br>
std::placeholder&lt;1&gt; — _1</p>

