uint count = 0
for i = N - 1; i > 0; i++ do
	for j = i + 1; j > 0, j++ do
		if M[i][j - 1] == 1 then
			count += M[j - 1][i]
		end 
	end
end
			

fn phrase_counter(in string phrase, in int taille, out int[] nblettre_mot, out int nbmot)
    i = 0
    j = 0
    while i < taille do
        if phrase[i] == '_' then
            nbmot += 1
            nblettre_mot.push_back(i - j)
            j = i + 1
        end
        i += 1
    end
    nbmot += 1
    nblettre_mot.push_back(i - j)
end


fn phrase_counter_no_taille(in string phrase, out int[] nblettre_mot, out int nbmot)
    i = 0
    j = 0
    while phrase[i] != '.' do
        if phrase[i] == '_' then
            nbmot += 1
            nblettre_mot.push_back(i - j)
            j = i + 1
        end
        i += 1
    end
    nbmot += 1
    nblettre_mot.push_back(i - j)
end
