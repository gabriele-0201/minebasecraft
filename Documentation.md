# World

World is divided in pieces, there is a coordinate system

## PieceOfWorld

There is also inside here a coordinate system, starting from 0,0,0 to nCubeSide, nCubeSide, ncubeHei

# Renderer

Ma chi cazzo renderizza cosa?? Perche' non ne ho la minima idea

Allora -> Il world dovrebbe tornare un qualcosa, i dati relativi a tutttto il mondo, compreso di qualsiasi cosa penso (in qualche modo anche settare i diversi materiali ecc penso anche se non ho idea di come farlo)
    
    Sicuramente Assieme ai veritici devo passare il tipo del blocco (quindi quale texture usare) e anche quale nulla
    Le TexCoord sono definite in funzione del tipo di pezzo

successivamente che il coso mi ha tornato tutto dovrei ricalcolare tutto in funzione della camera

Ricapotolandololo:

+ Dal World mi tiro fuori un array con tutti i veritici che sono da renderizzare (anche in numero di faccie cosi da capire come mettere l'index Buffer, anche se qui devo ancora capire bene come fare)

+ Successivamente imposto le matrici view a projection in funzione della camera, quindi in funzione di quello che torna il Player

+ Ed infine chiamo il draw di GL

# TODO

[ ] - impostare tutta la classe player
[ ] - Creare un correto vertex di ritorno dal world
[ ] - in qualche modo combinare le due cose precedenti
[ ] - NON far renderizzare facie tra pieceOfWorld