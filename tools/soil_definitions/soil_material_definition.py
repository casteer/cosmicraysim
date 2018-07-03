import periodictable
from periodictable import formula, mix_by_volume, mix_by_weight

def soil_material_definition(h2o_vol_fractions = [0.01, 0.02], pore_space = 0.5):

    for h2o_vol_fraction in h2o_vol_fractions:
	
        # Air taken from the definition of G4_AIR which is from Geant4's NIST database
	# print(formula("0.0124%wt C // 23.1781% O // 1.2827% Ar // N", natural_density=0.00120479))
        Air = formula("0.0124%wt C // 23.1781% O // 1.2827% Ar // N", natural_density=0.00120479)
        H2O = formula('H2O',natural_density=1)
        SiO2 = formula('SiO2',natural_density=2.65)

        mix = mix_by_volume(H2O,h2o_vol_fraction,SiO2,0.5,Air,0.5-h2o_vol_fraction);


        print ''
        print '{'
        print ' name: "MATERIAL", '
        print ' index: "SiO2_Air_H20_{0}",'.format(str(h2o_vol_fraction).replace('.','p'))


        print ' type: "compound",'
        keys = list(mix.mass_fraction.keys());


        print ' element_names: [',
        for k in keys:
            if(k!=keys[-1]):
                print '"{0}", '.format(str(k)),
            else:
                print '"{0}"]'.format(str(k))

        print ' element_counts: [',
        for k in keys:
            if(k!=keys[-1]):
                print '{0:.12f}, '.format(mix.mass_fraction[k]),
            else:
                print '{0:.12f}]'.format(mix.mass_fraction[k])

        print ' density: {0:.6f}'.format(mix.density)
        print ' density_units: "g/cm3"'
        print '}'
        print ''
