select * from tatertable;

select 	tatertable.refdate, geo_table.geo, tatertable.dguid, tatertable.areaproductionvalue, 
			uom_table.uom, tatertable.uomid, scalar_table.scalarfactor, tatertable.scalarid,
			tatertable.vector, tatertable.coordinate, tatertable.value, tatertable.status,
			tatertable.symbol, tatertable.terminated, tatertable.decimals
		from tatertable
		inner join geo_table
			on tatertable.dguid = geo_table.dguid
		inner join uom_table
			on tatertable.uomid = uom_table.uomid
		inner join scalar_table
			on tatertable.scalarid = scalar_table.scalarid
		order by tatertable.refdate, tatertable.dguid
		