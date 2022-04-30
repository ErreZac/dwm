void
grid(Monitor *m) {
	unsigned int i, n, cx, cy, cw, ch, aw, ah, cols, rows;
	Client *c;

	for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next))
		n++;

	/* grid dimensions */
	for(rows = 0; rows <= n/2; rows++)
		if(rows*rows >= n)
			break;
	cols = (rows && (rows - 1) * rows >= n) ? rows - 1 : rows;

	/* window geoms (cell height/width) */
	ch = m->wh / (rows ? rows : 1) - (rows ? rows + 1 : 2) * m->pertag->gappx[m->pertag->curtag];
	cw = m->ww / (cols ? cols : 1) - (rows ? rows + 1 : 2)*m->pertag->gappx[m->pertag->curtag];
	for(i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next)) {
		cx = m->wx + m->pertag->gappx[m->pertag->curtag] + (i / rows) * (cw + m->pertag->gappx[m->pertag->curtag]);
		cy = m->wy + m->pertag->gappx[m->pertag->curtag] + (i % rows) * (ch + m->pertag->gappx[m->pertag->curtag]);
		/* adjust height/width of last row/column's windows */
		ah = ((i + 1) % rows == 0) ? m->wh - (ch + m->pertag->gappx[m->pertag->curtag]) * rows : 0;
		aw = (i >= rows * (cols - 1)) ? m->ww - (cw + m->pertag->gappx[m->pertag->curtag]) * cols : 0;
		resize(c, cx, cy, cw - 2 * c->bw + aw, ch - 2 * c->bw + ah, False);
		i++;
	}
}
