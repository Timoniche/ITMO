---


---

<h1 id="signals">Signals</h1>
<p><strong>13.10.2018</strong><br>
вектор обработки (слотов - тот, кто подписан)</p>
<pre><code>struct signal {
    struct connection;
    typedef function&lt;void()&gt; slot;
    connection connect(slot s) {
	    slots.emplace_back(true, move(s));
    }
    void operator()() const {
	    rec_counter++;
	    for (auto&amp;&amp; p : slote) {
		    //try { s(); } 
		    //catch (...) { log("..."); }
		    if (p.first()) p.second();
	    }
	    --rec.counter;
	    if (rec.counter == 0) {
		    for (auto i = slots.begin(), i != slots.end(). ++i) {
			    if (i-&gt;first) ++i;
			    else i = slots.erase(i);
		    }
	    }
	}
private:
    vector&lt;slot&gt; slots;
}
struct signal::connection {
    connection(signal * sig, list&lt;slot&gt;::iterator it) : sig(sig), it(it) {}
    void disconnect() {
    if (sig-&gt;rec_counter == 0) {
	    sig-&gt;slots.erase(it);
    } else {
	    it-&gt;first = false;
    }
private:
	signal * sig;
	list&lt;slot&gt;::iterator it;
}
</code></pre>
<p><strong>reentrancy</strong></p>

<table>
<thead>
<tr>
<th>signal::op()</th>
<th></th>
<th></th>
</tr>
</thead>
<tbody>
<tr>
<td>A</td>
<td></td>
<td></td>
</tr>
<tr>
<td></td>
<td>signal::op()</td>
<td>B, disconnect(), cleanup</td>
</tr>
</tbody>
</table>
