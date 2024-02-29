prix_pate_pizza = 0.80
prix_pate_tarte = 0.60
prix_charbon = 0.25
prix_tomate = 0.3
prix_viande = 0.9
prix_oignon = 0.2
prix_lardons = 0.5
prix_creme = 0.4
prix_sauce = 0.35

prix_pizza = prix_pate_pizza + prix_charbon + prix_tomate + prix_viande + prix_oignon  + prix_sauce
prix_tarte_flambe = prix_pate_tarte + prix_charbon + prix_oignon + prix_lardons + prix_creme

print(f"Le prix de la pizza est de {prix_pizza} euros.")
print("Le prix de la tarte flambée est de", prix_tarte_flambe, "euros.")
print(f"Total: {prix_pizza + prix_tarte_flambe} euros.")